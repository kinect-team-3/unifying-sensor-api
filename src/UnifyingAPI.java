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
