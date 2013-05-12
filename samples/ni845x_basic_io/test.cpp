/* +---------------------------------------------------------------------------+
   |                 The Mobile Robot Programming Toolkit (MRPT)               |
   |                                                                           |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2013, Individual contributors, see AUTHORS file        |
   | Copyright (c) 2005-2013, MAPIR group, University of Malaga                |
   | Copyright (c) 2012-2013, University of Almeria                            |
   | All rights reserved.                                                      |
   |                                                                           |
   | Redistribution and use in source and binary forms, with or without        |
   | modification, are permitted provided that the following conditions are    |
   | met:                                                                      |
   |    * Redistributions of source code must retain the above copyright       |
   |      notice, this list of conditions and the following disclaimer.        |
   |    * Redistributions in binary form must reproduce the above copyright    |
   |      notice, this list of conditions and the following disclaimer in the  |
   |      documentation and/or other materials provided with the distribution. |
   |    * Neither the name of the copyright holders nor the                    |
   |      names of its contributors may be used to endorse or promote products |
   |      derived from this software without specific prior written permission.|
   |                                                                           |
   | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS       |
   | 'AS IS' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED |
   | TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR|
   | PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE |
   | FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL|
   | DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR|
   |  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)       |
   | HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,       |
   | STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN  |
   | ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           |
   | POSSIBILITY OF SUCH DAMAGE.                                               |
   +---------------------------------------------------------------------------+ */

#include <mrpt/hwdrivers/CInterfaceNI845x.h>
#include <mrpt/system.h>
#include <mrpt/gui.h>

using namespace std;
using namespace mrpt;
using namespace mrpt::gui;
using namespace mrpt::hwdrivers;


// ------------------------------------------------------
//				TestNI_USB_845x
// ------------------------------------------------------
void TestNI_USB_845x()
{
	CInterfaceNI845x  ni_usb;

	// Open first connected device:
	cout << "Openning device...\n";
	ni_usb.open(); 
	cout << "Done! Connected to: " << ni_usb.getDeviceDescriptor() << endl;

	ni_usb.setIOVoltageLevel( 25 ); // 2.5 volts
	
#if 0
	ni_usb.setIOPortDirection(0, 0xFF);
	while (!mrpt::system::os::kbhit())
	{
		ni_usb.writeIOPort(0, 0xFF); 
		mrpt::system::sleep(500);
		ni_usb.writeIOPort(0, 0x00); 
		mrpt::system::sleep(500);
	}
#endif

#if 0
	const size_t N=1000;
	std::vector<double> d0(N),d1(N),d2(N);

	ni_usb.setIOPortDirection(0, 0x00);
	for (size_t i=0;i<N;i++)
	{
		uint8_t d = ni_usb.readIOPort(0);
		mrpt::system::sleep(1);
		d0[i]= (d & 0x01) ? 1.0 : 0.0;
		d1[i]= (d & 0x02) ? 3.0 : 2.0;
		d2[i]= (d & 0x04) ? 5.0 : 4.0;
	}

	CDisplayWindowPlots win("Signals",640,480);

	win.hold_on();
	win.plot(d0, "b-");
	win.plot(d1, "r-");
	win.plot(d2, "k-");
	win.axis_fit();
	win.waitForKey();
#endif

#if 1
	ni_usb.create_SPI_configurations(1);
	ni_usb.set_SPI_configuration(0 /*idx*/, 0 /* CS */, 1000 /* Khz */, false /* clock_polarity_idle_high */, false /* clock_phase_first_edge */ );

	{
		const uint8_t write[2] = { 0x20, 0xFF };
		uint8_t read[2];
		size_t nRead;
		printf("TX: %02X %02X\n", write[0],write[1]);
		ni_usb.read_write_SPI(0 /* config idx */, 2, write, nRead, read );
	}

	const uint8_t write[2] = { 0x80 | 0x28, 0x00 };
	uint8_t read[2];
	size_t nRead;
	while (!mrpt::system::os::kbhit())
	{
		printf("TX: %02X %02X\n", write[0],write[1]);
		ni_usb.read_write_SPI(0 /* config idx */, 2, write, nRead, read );
		printf("RX: %02X %02X\n\n", read[0],read[1]);
		mrpt::system::sleep(100);
	}


#endif


	mrpt::system::pause();
}

// ------------------------------------------------------
//						MAIN
// ------------------------------------------------------
int main()
{
	try
	{
		TestNI_USB_845x();
		return 0;
	} catch (std::exception &e)
	{
		std::cout << "MRPT exception caught: " << e.what() << std::endl;
		return -1;
	}
}
