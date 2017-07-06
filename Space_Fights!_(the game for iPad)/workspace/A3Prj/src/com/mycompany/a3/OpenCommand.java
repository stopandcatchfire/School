package com.mycompany.a3;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class OpenCommand extends Command{
	private GameWorld g;
	private Sound op;
	
	public OpenCommand(GameWorld gw, Sound o){
		super("Open");
		this.g = gw;
		op = o;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.openDoor(op);
	
	}

}
