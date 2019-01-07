Domyślne okna dialogowe pod zmienną `JOptionPane`:

```
JOptionPane.showInputDialog("Wiadomosc");
```

Projektowanie własnego okna dialogowego: utworzenie obiektu JDialog
```
public class SampleDialog extends JDialog {
	JLabel sampleLabel = new JLabel("JAKIS PRZYKLADOWY TEKST");
	
	JPanel mainPanel = new JPanel();
	
	public SampleDialog() {
		mainPanel.add(sampleLabel);
		this.setSize(500, 500);
		this.setContentPane(mainPanel);
		this.setVisible(true);
	}
}
```
W klasie "okna rodzica" wystarczy wywołać konstuktor obiektu JDialog aby pojawił się na ekranie (o ile ma setVisible ustawione na `true`).