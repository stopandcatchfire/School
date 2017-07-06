package com.mycompany.a1;

import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class ContractCommand extends Command{
	private GameWorld g;
	
	public ContractCommand(GameWorld gw){
		super("Contract");
		this.g = gw;
	}
	
	@Override
	public void actionPerformed(ActionEvent evt){
		g.contract();
	}

}
