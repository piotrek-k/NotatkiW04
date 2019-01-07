## 1. Tworzenie klasy dziedziczącej po JPanel
```
public class DrawingPanel extends JPanel {
    @Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
        //rysowanie tutaj
    }
}
```

## 2. Umieszczenie panelu w oknie
Poprzez dodanie do głównego panelu
```
JPanel drawingPane = new DrawingPanel();
mainPanel.add(drawingPane);
```
Poprzez ustawienie DrawingPanel jako domyślnego w ramce
```
frame.setContentPane(new DrawingPanel());
```

## 3. Odświeżenie widoku
`repaint()` w JFrame.

## 4. Rysowanie
Użycie obiektu `Graphics g` wygenerowanego w punkcie 1.