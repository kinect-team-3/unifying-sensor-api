/**************************************************************
 This file is part of Kinect Sensor Architecture Development Project.

   Kinect Sensor Architecture Development Project is free software:
you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Kinect Sensor Architecture Development Project is distributed in
the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Kinect Sensor Architecture Development Project.  If
not, see <http://www.gnu.org/licenses/>.
**************************************************************/
/**************************************************************
The work was done in joint collaboration with Cisco Systems Inc.
Copyright © 2012, Cisco Systems, Inc. and UCLA
*************************************************************/

public class UnifyingAPI
{
	static byte[] process1 (byte[] bytestream)
	{
		byte[] res = { 0x0, 0x1, 0xf };
		return res;
	}
	native static String convert_raw_to_unified (byte[] data, int offset, int size,
			String type, String desc, String sensor);
			
	native static byte[] convert_unified_to_raw (String jsondata);
	
	// Public interface for process_unified
	public static String process_unified (String jsondata, String funcName)
	{
		int resCode;
		
		resCode = process_unified_native(funcName, jsondata);
		
		if (resCode == -1)
		{
			System.out.println("Cannot find function with the right signiture");
			return "";
		}
		else // resCode = 0, success
		{
			return result;
		}
	}
	
	// Native call to C function
	// return value is an error code
	private native static int process_unified_native (String funcName, String jsondata);
	
	// Member variable to hold the result of process_unified
	static String result;
	
	static
	{
		System.loadLibrary("CJavaInterface");
	}
}
