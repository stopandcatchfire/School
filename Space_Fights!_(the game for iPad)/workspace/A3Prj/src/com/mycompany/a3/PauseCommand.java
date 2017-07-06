package com.mycompany.a3;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class PauseCommand extends Command{
	private Game g;
	boolean flg = false;
	
	public PauseCommand(Game g){
		super("Pause");
		this.g = g;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		flg = !flg;
		g.pause(flg);	
	}

	
	
}
