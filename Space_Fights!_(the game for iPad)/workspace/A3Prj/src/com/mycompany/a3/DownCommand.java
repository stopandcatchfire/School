package com.mycompany.a3;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class DownCommand extends Command{
	private GameWorld g;
	
	public DownCommand(GameWorld gw){
		super("Down");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.moveDown();
	}

}
