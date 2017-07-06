package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class UpCommand extends Command{
	private GameWorld g;
	
	public UpCommand(GameWorld gw){
		super("Up");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.moveUp();
	}

}
