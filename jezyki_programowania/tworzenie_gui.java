package gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class MainWindow extends JFrame implements ActionListener {

	private static final long serialVersionUID = 6508677434934299276L;

	public static void main(String[] args) {
		new MainWindow(); //wywołanie konstruktora tworzącego okno apikacji
	}
	
	public MainWindow() {
		// Konstruktor, utworzenie okna aplikacji
		
		setTitle("PersonWindowApp");  
		setDefaultCloseOperation(DISPOSE_ON_CLOSE);
		setSize(270, 270);
		setResizable(false);
		setLocationRelativeTo(null);
		
		// Dodanie słuchaczy zdarzeń do przycisków
		//newButton.addActionListener(this);
		
		// Główny panel okna aplikacji
		JPanel panel = new JPanel();
		
		// Dodanie komponentów
		//panel.add(firstNameLabel);
		
		// Umieszczenie Panelu w głównym oknie aplikacji.
		setContentPane(panel);
		
		// Pokazanie okna aplikacji na ekranie. Uruchomienie głównej pętli zdarzeń
		setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		Object eventSource = e.getSource();
		
		//if (eventSource == newButton) { 
			// pzycisk kliknięty
		//}
	}
}
