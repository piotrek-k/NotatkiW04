Implementacja poniższych klas:
```MouseListener, MouseMotionListener, KeyListener```

W konstruktorze JPanelu, deklaracja listenerów:
```
this.setFocusable(true);
this.addMouseListener(this);
this.addMouseMotionListener(this);
this.addKeyListener(this);
```

Eclipse potrafi wygenerować potrzebne metody automatycznie, dane na temat zdarzenia po zmienną `e`.