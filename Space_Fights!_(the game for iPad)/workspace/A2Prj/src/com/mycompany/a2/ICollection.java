package com.mycompany.a2;



/*
 * Decided not to implement this yet, I imagine I will utilize it properly
 * once we implement a proper iterator.
 */
public interface ICollection{
	
	public void add(GameObject newObject);
	
	public IIterator getIterator();

}
