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

import java.io.*;
import java.util.Scanner;

public class HelloWorld
{
    public static void main(String[] args) throws IOException
    {
		String text = new String();
        Scanner scanner = new Scanner(new FileInputStream("../flower.json"));
		try
		{
			while (scanner.hasNextLine())
			{
				text = text + scanner.nextLine();
			}
		}
		catch (Exception e)
		{
				System.err.println(e.getMessage());
		}
		finally
		{
			scanner.close();
		}
		byte[] flower = null;
		flower = UnifyingAPI.convert_unified_to_raw(text);
		for (byte b : flower)
			System.out.printf("%x", b);
		System.out.println();
		
    }

}
