package com.mycompany.a3;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class TickCommand extends Command{
	private GameWorld g;
	
	public TickCommand(GameWorld gw){
		super("Tick");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		//g.tickClock();
	}

}
