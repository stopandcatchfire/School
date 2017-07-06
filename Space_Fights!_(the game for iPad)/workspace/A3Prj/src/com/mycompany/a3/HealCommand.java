package com.mycompany.a3;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class HealCommand extends Command{
	private GameWorld g;
	private IIterator it;
	private GameObject o;
	
	public HealCommand(GameWorld gw){
		super("Heal");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		it = g.getIterator(true);
		while(it.hasNext()){
			if((o=it.getNext()) instanceof Astronaut){
				Astronaut a = (Astronaut) o;
				if(a.getSelected() && g.getPaused())
					a.setHealth(5);
			}
		}
	}


}
