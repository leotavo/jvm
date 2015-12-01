public abstract class Attribute 
{
	public abstract String getAttributeName();
	public abstract byte[] getExtraBytes();
	
	public final int getAttributeSize()
	{
		return getExtraBytes().length;
	}
}
