package com.mycompany.a2;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class JumpAstronautCommand extends Command{
	private GameWorld g;
	
	public JumpAstronautCommand(GameWorld gw){
		super("MoveToAstronaut");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.jumpToAstronaut();
	}

}
