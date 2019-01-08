Przykład:

```
public static void saveAsBinary(String file_name, Book book) throws BookException {
		try {
			FileOutputStream fileOut = new FileOutputStream(file_name);
			ObjectOutputStream out = new ObjectOutputStream(fileOut);
			out.writeObject(book);
			out.close();
			fileOut.close();
		} catch (FileNotFoundException e) {
			throw new BookException("Nie odnaleziono pliku " + file_name);
		} catch (IOException i) {
			throw new BookException("Wystąpił problem z zapisem do " + file_name);
		}
	}
```

Wybór pliku z dysku:
```
/**
	 * Wyświetla okno wyboru lokalizacji pliku, zwraca nazwę wybranego pliku
	 */
	private String askUserForFileName() throws BookException {
		JFileChooser chooser = new JFileChooser();
		String fileName = "";

		int returnVal = chooser.showOpenDialog(frame);
		if (returnVal == JFileChooser.APPROVE_OPTION) {
			fileName = chooser.getSelectedFile().getAbsolutePath();
		}

		if (fileName == null || fileName.equals(""))
			throw new BookException("Nazwa pliku musi zostać podana");

		return fileName;
	}
```