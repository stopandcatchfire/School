package com.mycompany.a2;

import java.util.Vector;

public class SpaceCollection implements ICollection{
	
	private Vector<GameObject> theCollection;
	
	public SpaceCollection(){
		theCollection = new Vector<GameObject>();
	}
	
	public void add(GameObject o){
		theCollection.addElement(o);
	}
	
	public IIterator getIterator(){
		return new SpaceIterator();
	}
	
	public int size(){
		return theCollection.size();
	}
	
	private class SpaceIterator implements IIterator{
		
		private int index;
		
		public SpaceIterator(){
			index = -1;
		}
		
		public boolean hasNext() {
			if(theCollection.size() <= 0)
				return false;
			if(index == theCollection.size() - 1)
				return false;
			return true;
		}
		
		public GameObject getNext(){
			index++;
			return theCollection.elementAt(index);
		}

		public void remove(GameObject o){
			theCollection.remove(o);
			index--;
		}
		
		
	}

}
