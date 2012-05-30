public class UnifyingAPI
{
	native static String convert_raw_to_unified(byte[] data, int offset, int size,
			String type, String desc, String sensor);
			
	native static byte[] convert_unified_to_raw (String jsondata);
	
	static
	{
		System.loadLibrary("CJavaInterface");
	}
}
