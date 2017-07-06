package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class OpenCommand extends Command{
	private GameWorld g;
	
	public OpenCommand(GameWorld gw){
		super("Open");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.openDoor();
	
	}

}
