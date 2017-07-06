package com.mycompany.a2;
import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Button;
import com.codename1.ui.CheckBox;
import com.codename1.ui.Command;
import com.codename1.ui.Component;
import com.codename1.ui.Container;
import com.codename1.ui.Dialog;
import com.codename1.ui.Form;
import com.codename1.ui.Toolbar;
import com.codename1.ui.layouts.BorderLayout;
import com.codename1.ui.layouts.BoxLayout;
import com.codename1.ui.layouts.FlowLayout;
import com.codename1.ui.plaf.Border;

/*
 * Game is the class that handles gameworld instantiation and user input.
 * Creates text field on simulation screen.  Takes in user input from textField
 * on screen and calls the various methods in gameworld.
 */

public class Game extends Form {
	
	private GameWorld gw;
	//private boolean exitFlag = false;
	private MapView mv;
	private ScoreView sv;
	//private Container cont;
	
	public Game(){
			gw = new GameWorld();
			gw.init();
			mv = new MapView(gw);
			sv = new ScoreView(gw);
			gw.addObserver(mv);
			gw.addObserver(sv);
			
			//sets dimensions for gameworld
			gw.setHeight(mv.getHeight());
			gw.setWidth(mv.getWidth());
			
			Toolbar myToolbar = new Toolbar();
			
			this.setLayout(new BorderLayout());
			this.add(BorderLayout.NORTH, sv);
			this.add(BorderLayout.CENTER, mv);
			
			Container leftContainer = new Container(new BoxLayout(BoxLayout.Y_AXIS));
			Container rightContainer = new Container(new BoxLayout(BoxLayout.Y_AXIS));
			Container bottomContainer = new Container(new FlowLayout(Component.CENTER));
			leftContainer.getAllStyles().setPadding(RIGHT, 50);
			leftContainer.getAllStyles().setPadding(TOP, 300);
			leftContainer.getAllStyles().setBorder(Border.createLineBorder(5, ColorUtil.BLUE));
			rightContainer.getAllStyles().setPadding(RIGHT, 50);
			rightContainer.getAllStyles().setPadding(TOP, 300);
			rightContainer.getAllStyles().setBorder(Border.createLineBorder(5, ColorUtil.BLUE));
			bottomContainer.getAllStyles().setAlignment(CENTER);
			bottomContainer.getAllStyles().setPadding(RIGHT, 50);
			bottomContainer.getAllStyles().setBorder(Border.createLineBorder(5, ColorUtil.BLUE));
			sv.getAllStyles().setBorder(Border.createLineBorder(5,ColorUtil.GREEN));
			mv.getAllStyles().setBorder(Border.createLineBorder(5, ColorUtil.BLACK));
			
			
			
			//Creating Buttons for GUI
			Button up = new Button("Up");		
			Button left = new Button("Left");			
			Button right = new Button("Right");		
			Button down = new Button("Down");
			Button expandButton = new Button("Expand");
			Button moveAstro = new Button("MoveToAstronaut");
			Button contract = new Button("Contract");
			Button moveAlien = new Button("MoveToAlien");
			Button score = new Button("Score");
			Button newAlien = new Button("NewAlien");
			Button fight = new Button("NewAlien");
			Button tick = new Button("Tick");
			
			
			
			
			//setting button color
			up.getAllStyles().setBgColor(ColorUtil.BLUE);
			up.getAllStyles().setBgTransparency(255);
			left.getAllStyles().setBgColor(ColorUtil.BLUE);
			left.getAllStyles().setBgTransparency(255);
			right.getAllStyles().setBgColor(ColorUtil.BLUE);
			right.getAllStyles().setBgTransparency(255);
			down.getAllStyles().setBgColor(ColorUtil.BLUE);
			down.getAllStyles().setBgTransparency(255);
			expandButton.getAllStyles().setBgColor(ColorUtil.BLUE);
			expandButton.getAllStyles().setBgTransparency(255);
			moveAstro.getAllStyles().setBgColor(ColorUtil.BLUE);
			moveAstro.getAllStyles().setBgTransparency(255);
			contract.getAllStyles().setBgColor(ColorUtil.BLUE);
			contract.getAllStyles().setBgTransparency(255);
			moveAlien.getAllStyles().setBgColor(ColorUtil.BLUE);
			moveAlien.getAllStyles().setBgTransparency(255);
			score.getAllStyles().setBgColor(ColorUtil.BLUE);
			score.getAllStyles().setBgTransparency(255);
			newAlien.getAllStyles().setBgColor(ColorUtil.BLUE);
			newAlien.getAllStyles().setBgTransparency(255);
			fight.getAllStyles().setBgColor(ColorUtil.rgb(255, 0, 0));
			fight.getAllStyles().setBgTransparency(255);
			tick.getAllStyles().setBgColor(ColorUtil.BLUE);
			tick.getAllStyles().setBgTransparency(255);
			
			//Instantiating Command objects and associating them with their buttons and keys
			ExpandCommand expandCommand = new ExpandCommand(gw);
			expandButton.setCommand(expandCommand);
			addKeyListener('e', expandCommand);
			
			ContractCommand contCommand = new ContractCommand(gw);
			contract.setCommand(contCommand);
			addKeyListener('c', contCommand);
			
			UpCommand upCommand = new UpCommand(gw);
			up.setCommand(upCommand);
			addKeyListener('u', upCommand);
			
			LeftCommand leftCommand = new LeftCommand(gw);
			left.setCommand(leftCommand);
			addKeyListener('l', leftCommand);
			
			RightCommand rightCommand = new RightCommand(gw);
			right.setCommand(rightCommand);
			addKeyListener('r', rightCommand);
			
			DownCommand downCommand = new DownCommand(gw);
			down.setCommand(downCommand);
			addKeyListener('d', downCommand);
			
			JumpAstronautCommand ja = new JumpAstronautCommand(gw);
			moveAstro.setCommand(ja);
			addKeyListener('o', ja);
			
			JumpAlienCommand jl = new JumpAlienCommand(gw);
			moveAlien.setCommand(jl);
			addKeyListener('a', jl);
			
			OpenCommand openDoor = new OpenCommand(gw);
			score.setCommand(openDoor);
			addKeyListener('s', openDoor);
			
			AlienCollisionCommand acc = new AlienCollisionCommand(gw);
			newAlien.setCommand(acc);
			addKeyListener('w', acc);
			
			FightCommand fc = new FightCommand(gw);
			fight.setCommand(fc);
			addKeyListener('f', fc);
			
			TickCommand tc = new TickCommand(gw);
			tick.setCommand(tc);
			addKeyListener('t', tc);
			
			
			//Titlebar elements (including Side Menu)
			setToolbar(myToolbar);
			this.setTitle("Space Fights");
			
			myToolbar.addCommandToSideMenu(openDoor);
			
			AboutCommand about = new AboutCommand();
			myToolbar.addCommandToSideMenu(about);
			
			ExitCommand exit = new ExitCommand();
			myToolbar.addCommandToSideMenu(exit);
			addKeyListener('x', exit);
			
			SoundCommand sound = new SoundCommand(gw);
			CheckBox soundCheck = new CheckBox("Sound");
			soundCheck.setCommand(sound);
			myToolbar.addComponentToSideMenu(soundCheck);
			
			HelpCommand help = new HelpCommand();
			myToolbar.addCommandToRightBar(help);
			
			//Adding buttons to Containers
			leftContainer.add(expandButton);	
			leftContainer.add(up);
			leftContainer.add(left);
			leftContainer.add(moveAstro);
			rightContainer.add(contract);
			rightContainer.add(down);
			rightContainer.add(right);
			rightContainer.add(moveAlien);
			rightContainer.add(score);
			bottomContainer.add(newAlien);
			bottomContainer.add(fight);
			bottomContainer.add(tick);
			
			//add containers to form
			this.add(BorderLayout.WEST, leftContainer);
			this.add(BorderLayout.EAST, rightContainer);
			this.add(BorderLayout.SOUTH, bottomContainer);
			
			this.show();
	}
}
