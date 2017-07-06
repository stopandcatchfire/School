package com.mycompany.a2;

public interface IIterator {
	
	public boolean hasNext();
	
	public GameObject getNext();
	
	public void remove(GameObject o);
}
