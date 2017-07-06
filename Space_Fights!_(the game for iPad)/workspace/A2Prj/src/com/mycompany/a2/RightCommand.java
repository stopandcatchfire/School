package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class RightCommand extends Command{
	private GameWorld g;
	
	public RightCommand(GameWorld gw){
		super("Right");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.moveRight();
	}

}
