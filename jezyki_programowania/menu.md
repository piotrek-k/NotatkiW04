Pasek menu na górze ekranu:
```
JMenuBar menuBar = new JMenuBar();
```

Rozwijana lista menu:
```
JMenu listOfMenuButtons = new JMenu("OPCJE");
```

Opcje w rozwijanej liście:
```
JMenuItem authorButton = new JMenuItem("AUTOR");
JMenuItem aboutButton = new JMenuItem("O PROGRAMIE");
JMenuItem exitButton = new JMenuItem("WYJŚCIE");
```

Dodanie do widoku:
```
listOfMenuButtons.add(authorButton);
listOfMenuButtons.add(aboutButton);
listOfMenuButtons.add(exitButton);
menuBar.add(listOfMenuButtons);
this.setJMenuBar(menuBar);
```

W celu wykrycia kliknięcia, należy wcześniej dodać listenery:
```
authorButton.addActionListener(this);
aboutButton.addActionListener(this);
exitButton.addActionListener(this);
```

Wykrywanie akcji:
```
@Override
public void actionPerformed(ActionEvent e) {
    // TODO Auto-generated method stub
    Object source = e.getSource();
    if(source == exitButton) {
        this.dispose();
    }
}
```