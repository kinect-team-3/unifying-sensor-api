import java.io.*;
import java.util.Scanner;

public class HelloWorld
{
	// Sample process function: turn the raw data into the 0xabcde
/*
	private int process1 (byte[] bytestream)
	{
		bytestream = new byte[]{ 0xa, 0xb, 0xc, 0xd, 0xe };
		return 0;
	}
*/

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
		
		System.out.println ("Converting back to JSON");
		
		String json = UnifyingAPI.convert_raw_to_unified(flower, 0, flower.length,
										"JPEG", "JPEG is an image format", "Kinect");
		
		System.out.println(json);
		System.out.println();
		System.out.println("Testing process_unified");
		
		json = UnifyingAPI.process_unified(json, "process1");
		
		System.out.println(json);
		
    }

}
