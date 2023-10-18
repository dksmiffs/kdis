/**********************************************************************
The following UNLICENSE statement applies to this example.

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
*********************************************************************/

/*********************************************************************
For Further Information on KDIS:
http://p.sf.net/kdis/UserGuide

This example is based on PDU_Factory2 example however it shows how the
ConnectionAddressFilter can be used to block/allow particular IP addresses.
If you want to test this you will need an other machine generating DIS to see
the filter in action.
*********************************************************************/

#include <iostream>

#include "KDIS/Extras/PDU_Factory.hpp"
#include "KDIS/Network/Connection.hpp"
#include "KDIS/Network/ConnectionAddressFilter.hpp"
#include "KDIS/PDU/Distributed_Emission_Regeneration/Designator_PDU.hpp"

using namespace std;
using namespace KDIS;
using namespace PDU;
using namespace NETWORK;

int main() {
  Designator_PDU a;
  a.SetExerciseID(12);
  const auto aa = KDIS::PDU::clone(a);
  a.SetExerciseID(100);
  std::cout << "A: " << std::to_string(a.GetExerciseID())
            << "AA: " << std::to_string(aa->GetExerciseID()) << std::endl;
  Header b;
  b.SetExerciseID(22);
  const auto bb = KDIS::PDU::clone(b);
  b.SetExerciseID(200);
  std::cout << "B: " << std::to_string(b.GetExerciseID())
            << "BB: " << std::to_string(bb->GetExerciseID()) << std::endl;

  try {
    // Note this multi cast address will probably be different for your network
    // however port 3000 is the assigned number by IANA(Internet Assigned
    // Numbers Authority) for DIS simulations.
    Connection conn("192.168.3.255");

    // Create the filter and set it up so it only allows our test machine
    // through.
    ConnectionAddressFilter filter(
        ConnectionAddressFilter::
            AllowAddressesInFilterList);  // Only allow address we add through.
    // ConnectionAddressFilter filter(
    // ConnectionAddressFilter::BlockAddressesInFilterList ); // Block the
    // address we add and allow all others through.

    filter.AddAddress("192.168.3.241");  // This should be the address of your
                                         // other DIS machine
    // filter.AddAddress( "192.168.3.124" ); // Add an other machine?

    // Add our filter
    conn.AddSubscriber(&filter);

    while (true) {
      try {
        unique_ptr<Header> pHeader = conn.GetNextPDU();
        if (pHeader.get()) {
          cout << pHeader->GetAsString() << endl;
        }
      } catch (exception& e) {
        // KDIS error, should be safe to carry on.
        cout << e.what() << endl;
      }
    }
  } catch (exception& e) {
    // Socket/Connection error, better stop.
    cout << e.what() << endl;
  }

  return 0;
}
