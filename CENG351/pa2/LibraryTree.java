import java.util.*;
public class LibraryTree {

	public LibraryNode primaryRoot;		//root of the primary B+ tree
	public LibraryNode secondaryRoot;	//root of the secondary B+ tree
	public Integer order;
	public LibraryTree(Integer order)
	{
		this.order = order;
		LibraryNode.order = order;
		primaryRoot = new LibraryNodeLeaf(null);
		primaryRoot.level = 0;
		secondaryRoot = new LibraryNodeLeaf(null);
		secondaryRoot.level = 0;
	}

	public void addBook(CengBook book) {
		addToPrimary(book);
		addToSecondary(book);
	}

	private void addToSecondary(CengBook book) {
		LibraryNodeLeaf leaf = (LibraryNodeLeaf)searchSecondary(book, secondaryRoot);
		ArrayList<CengBook> books = leaf.getbooks();
		//add the current book to the corresponding leaf
		books.add(book);
		Collections.sort(books, new Comparator<CengBook>() {
			public int compare(CengBook b1, CengBook b2) {
				if(b1.year().equals(b2.year())) {
					return b1.key() - b2.key();
				}else {
					return b1.year() - b2.year();
				}
			}
		});

		//handle the leaf overflow (easy one)
		if(overflow(books)) {
			LibraryNode p = leaf.getParent();

			//case 1: root is the leaf
			LibraryNodeSecondaryIndex parent;
			if(p == null) {
				parent = new LibraryNodeSecondaryIndex(p);

				LibraryNodeLeaf left = new LibraryNodeLeaf(parent);
				LibraryNodeLeaf right = new LibraryNodeLeaf(parent);

				ArrayList<CengBook> l_books = left.getbooks();
				ArrayList<CengBook> r_books = right.getbooks();

				//split elements into two lists
				int index = (int)(Math.ceil(2*this.order / 2.0 ));
				int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));
				for(int i=0; i<split; i++) {
					l_books.add(books.get(i));
				}
				for(int i=split; i<books.size(); i++) {
					r_books.add(books.get(i));
				}
				parent.addKey(books.get(split).key());
				parent.addYear(books.get(split).year());
				parent.addChild(left);
				parent.addChild(right);

				secondaryRoot = parent;
				return;
				//case 2: there are internal nodes
			}else {
				parent = (LibraryNodeSecondaryIndex)p;

				LibraryNodeLeaf right = new LibraryNodeLeaf(parent);
				ArrayList<CengBook> r_books = right.getbooks();

				//move the corresponding elements to the new list
				int index = (int)(Math.ceil(2*this.order / 2.0 ));
				int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));
				for(int i=split; i<books.size(); i++) {
					r_books.add(books.get(i));
				}

				Integer key = books.get(split).key();
				Integer year = books.get(split).year();
				for(int i=books.size()-1; i>=split; i--) {
					books.remove(i);
				}

				parent.add(year, key, right);
			}

			// handle the internal overflows(complicated one)
			while(parent.overflow(order)) {
				//case 1: should expand root
				if(parent.getParent() == null) {
					LibraryNodeSecondaryIndex n_parent = new LibraryNodeSecondaryIndex(null);
					LibraryNodeSecondaryIndex left = new LibraryNodeSecondaryIndex(n_parent);
					LibraryNodeSecondaryIndex right = new LibraryNodeSecondaryIndex(n_parent);

					int index = (int)(Math.ceil(2*this.order / 2.0 ));
					int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));

					for(int i=0; i<split; i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(left);
						left.addKey(parent.keyAtIndex(i));
						left.addYear(parent.yearAtIndex(i));
						left.addChild(child);
					}
					left.addChild(parent.getChildrenAt(split));
					parent.getChildrenAt(split).setParent(left);
					for(int i=split + 1; i<parent.childrenCount(); i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(right);
						right.addKey(parent.keyAtIndex(i));
						right.addYear(parent.yearAtIndex(i));
						right.addChild(child);
					}

					n_parent.addKey(parent.keyAtIndex(split));
					n_parent.addYear(parent.yearAtIndex(split));
					n_parent.addChild(left);
					n_parent.addChild(right);

					secondaryRoot = n_parent;
					break;
					//case 2: internal node except root
				}else {
					LibraryNodeSecondaryIndex r_root = (LibraryNodeSecondaryIndex)parent.getParent();

					LibraryNodeSecondaryIndex left = new LibraryNodeSecondaryIndex(r_root);
					LibraryNodeSecondaryIndex right = new LibraryNodeSecondaryIndex(r_root);

					int index = (int)(Math.ceil(2*this.order / 2.0 ));
					int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));
					Integer key = parent.keyAtIndex(split);
					Integer year = parent.yearAtIndex(split);

					// ArrayList<Integer> keys = r_root.getKeys();
					ArrayList<Integer> keys = r_root.getKeys();
					ArrayList<Integer> years = r_root.getYears();
					ArrayList<LibraryNode> children = r_root.getAllChildren();

					int insert = r_root.search(year, key);
					insert = insert >= 0 ? insert : -insert - 1;

					children.remove(insert);

					for(int i=0; i<split; i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(left);
						left.addKey(parent.keyAtIndex(i));
						left.addYear(parent.yearAtIndex(i));
						left.addChild(child);
					}
					left.addChild(parent.getChildrenAt(split));
					parent.getChildrenAt(split).setParent(left);
					for(int i=split + 1; i<parent.childrenCount(); i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(right);
						right.addKey(parent.keyAtIndex(i));
						right.addYear(parent.yearAtIndex(i));
						right.addChild(child);
					}

					keys.add(insert, key);
					years.add(insert, year);
					children.add(insert, left);
					children.add(insert+1, right);

					parent = r_root;
				}
			}
		}
	}

	private LibraryNode searchSecondary(CengBook book, LibraryNode root) {
		if(root.getType() == LibraryNodeType.Leaf) {
			return root;
		}else {
			LibraryNodeSecondaryIndex node = (LibraryNodeSecondaryIndex)root;
			int index = node.search(book.year(), book.key());

			return searchSecondary(book, node.getChildrenAt(index));
		}
	}

	private void addToPrimary(CengBook book) {
		LibraryNodeLeaf leaf = (LibraryNodeLeaf)searchPrimary(book, primaryRoot);
		ArrayList<CengBook> books = leaf.getbooks();
		//add the current book to the corresponding leaf
		books.add(book);
		Collections.sort(books, (b1, b2) -> b1.key() - b2.key());

		//handle the leaf overflow (easy one)
		if(overflow(books)) {
			LibraryNode p = leaf.getParent();

			//case 1: root is the leaf
			LibraryNodePrimaryIndex parent;
			if(p == null) {
				parent = new LibraryNodePrimaryIndex(p);

				LibraryNodeLeaf left = new LibraryNodeLeaf(parent);
				LibraryNodeLeaf right = new LibraryNodeLeaf(parent);

				ArrayList<CengBook> l_books = left.getbooks();
				ArrayList<CengBook> r_books = right.getbooks();

				//split elements into two lists
				int index = (int)(Math.ceil(2*this.order / 2.0 ));
				int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));
				for(int i=0; i<split; i++) {
					l_books.add(books.get(i));
				}
				for(int i=split; i<books.size(); i++) {
					r_books.add(books.get(i));
				}
				parent.addKey(books.get(split).key());
				Collections.sort(parent.getKeys());
				parent.addChild(left);
				parent.addChild(right);

				primaryRoot = parent;
				return;
				//case 2: there are internal nodes
			}else {
				parent = (LibraryNodePrimaryIndex)p;

				LibraryNodeLeaf right = new LibraryNodeLeaf(parent);
				ArrayList<CengBook> r_books = right.getbooks();

				//move the corresponding elements to the new list
				int index = (int)(Math.ceil(2*this.order / 2.0 ));
				int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));
				for(int i=split; i<books.size(); i++) {
					r_books.add(books.get(i));
				}

				Integer key = books.get(split).key();
				for(int i=books.size()-1; i>=split; i--) {
					books.remove(i);
				}

				parent.addPair(key, right);
			}

			// handle the internal overflows(complicated one)
			while(parent.overflow(order)) {
				//case 1: should expand root
				if(parent.getParent() == null) {
					LibraryNodePrimaryIndex n_parent = new LibraryNodePrimaryIndex(null);
					LibraryNodePrimaryIndex left = new LibraryNodePrimaryIndex(n_parent);
					LibraryNodePrimaryIndex right = new LibraryNodePrimaryIndex(n_parent);

					int index = (int)(Math.ceil(2*this.order / 2.0 ));
					int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));

					for(int i=0; i<split; i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(left);
						left.addKey(parent.keyAtIndex(i));
						left.addChild(child);
					}
					left.addChild(parent.getChildrenAt(split));
					parent.getChildrenAt(split).setParent(left);
					for(int i=split + 1; i<parent.childrenCount(); i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(right);
						right.addKey(parent.keyAtIndex(i));
						right.addChild(child);
					}

					n_parent.addKey(parent.keyAtIndex(split));
					n_parent.addChild(left);
					n_parent.addChild(right);

					primaryRoot = n_parent;
					break;
					//case 2: internal node except root
				}else {
					LibraryNodePrimaryIndex r_root = (LibraryNodePrimaryIndex)parent.getParent();

					LibraryNodePrimaryIndex left = new LibraryNodePrimaryIndex(r_root);
					LibraryNodePrimaryIndex right = new LibraryNodePrimaryIndex(r_root);

					int index = (int)(Math.ceil(2*this.order / 2.0 ));
					int split = (int)(Math.ceil((2*this.order - 1) / 2.0 ));
					Integer key = parent.keyAtIndex(split);

					ArrayList<Integer> keys = r_root.getKeys();
					ArrayList<LibraryNode> children = r_root.getAllChildren();

					int insert = Collections.binarySearch(keys, key);
					insert = insert >= 0 ? insert : -insert - 1;

					children.remove(insert);

					for(int i=0; i<split; i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(left);
						left.addKey(parent.keyAtIndex(i));
						left.addChild(child);
					}
					left.addChild(parent.getChildrenAt(split));
					parent.getChildrenAt(split).setParent(left);
					for(int i=split + 1; i<parent.childrenCount(); i++) {
						LibraryNode child = parent.getChildrenAt(i);
						child.setParent(right);
						right.addKey(parent.keyAtIndex(i));
						right.addChild(child);
					}

					keys.add(insert, key);
					children.add(insert, left);
					children.add(insert+1, right);

					parent = r_root;
				}
			}
		}
	}

	private LibraryNode searchPrimary(CengBook book, LibraryNode root) {
		if(root.getType() == LibraryNodeType.Leaf) {
			return root;
		}else {
			LibraryNodePrimaryIndex node = (LibraryNodePrimaryIndex)root;
			int index=0;
			index = Collections.binarySearch(node.getKeys(), book.key());
			index = index > 0 ? index : -index - 1;

			return searchPrimary(book, node.getChildrenAt(index));
		}
	}


	public CengBook searchBook(Integer key) {
		searchBook(primaryRoot, key);
		// add methods to find the book with the searched key in primary B+ tree
		// return value will not be tested, just print as the specicifications say
		return null;
	}

	public void searchBook(LibraryNode localroot, Integer key) {
		if(localroot == null) {
			System.out.println("Something is definitely wrong");
		}else if(localroot.type == LibraryNodeType.Leaf) {
			LibraryNodeLeaf leaf = (LibraryNodeLeaf)localroot;

			boolean done = false;
			for(CengBook book : leaf.getbooks()) {
				if(key.equals(book.key())) {
					done = true;
					Integer book_key = book.key();
					Integer year = book.year();
					String name = book.name();
					String author = book.author();
					StringBuilder sb = new StringBuilder();
					sb.append("<data>");
					sb.append("\n");
					sb.append("<record>");
					sb.append(book_key);
					sb.append("|");
					sb.append(year);
					sb.append("|");
					sb.append(name);
					sb.append("|");
					sb.append(author);
					sb.append("</record>");
					sb.append("\n");
					sb.append("</data>");
					System.out.println(sb.toString());
					break;
				}
			}
			if(!done) {
				System.out.println("No match for " + key);
			}
		}else {
			LibraryNodePrimaryIndex internal = (LibraryNodePrimaryIndex)localroot;
			ArrayList<Integer> keys = internal.getKeys();
			int index = Collections.binarySearch(keys, key);

			index = index >= 0 ? index + 1 : -index - 1;
			StringBuilder sb = new StringBuilder();

			sb.append("<index>\n");
			for(Integer i : keys) {
				sb.append(i);
				sb.append("\n");
			}
			sb.append("</index>");

			System.out.println(sb.toString());

			searchBook(internal.getChildrenAt(index), key);
		}
	}


	public void printPrimaryLibrary() {
		printPrimaryLibrary(primaryRoot);
		// myPrint(primaryRoot);
		// add methods to print the primary B+ tree in Depth-first order
	}

	public void printPrimaryLibrary(LibraryNode root) {
		if(root.getType() == LibraryNodeType.Leaf) {
			LibraryNodeLeaf leaf = (LibraryNodeLeaf)root;
			ArrayList<CengBook> books = leaf.getbooks();

			StringBuilder sb = new StringBuilder();
			sb.append("<data>");
			sb.append("\n");
			for(CengBook book : books) {
				Integer book_key = book.key();
				Integer year = book.year();
				String name = book.name();
				String author = book.author();
				sb.append("<record>");
				sb.append(book_key);
				sb.append("|");
				sb.append(year);
				sb.append("|");
				sb.append(name);
				sb.append("|");
				sb.append(author);
				sb.append("</record>");
				sb.append("\n");
			}
			sb.append("</data>");
			System.out.println(sb.toString());
		}else {
			LibraryNodePrimaryIndex internal = (LibraryNodePrimaryIndex)root;
			StringBuilder sb = new StringBuilder();
			sb.append("<index>\n");
			for(int i=0; i<internal.keyCount(); i++) {
				sb.append(internal.keyAtIndex(i));
				sb.append("\n");
			}
			sb.append("</index>");
			System.out.println(sb.toString());
			for(int i=0; i<internal.childrenCount(); i++) {
				printPrimaryLibrary(internal.getChildrenAt(i));
			}
		}
	}


	public void printSecondaryLibrary() {
		printSecondaryLibrary(secondaryRoot);
		// add methods to print the secondary B+ tree in Depth-first order

	}

	public void printSecondaryLibrary(LibraryNode root) {
		if(root.getType() == LibraryNodeType.Leaf) {
			LibraryNodeLeaf leaf = (LibraryNodeLeaf)root;
			ArrayList<CengBook> books = leaf.getbooks();

			StringBuilder sb = new StringBuilder();
			sb.append("<data>");
			sb.append("\n");
			for(CengBook book : books) {
				Integer book_key = book.key();
				Integer year = book.year();
				String name = book.name();
				String author = book.author();
				sb.append("<record>");
				sb.append(book_key);
				sb.append("|");
				sb.append(year);
				sb.append("|");
				sb.append(name);
				sb.append("|");
				sb.append(author);
				sb.append("</record>");
				sb.append("\n");
			}
			sb.append("</data>");
			System.out.println(sb.toString());
		}else {
			LibraryNodeSecondaryIndex internal = (LibraryNodeSecondaryIndex)root;
			StringBuilder sb = new StringBuilder();
			sb.append("<index>\n");
			for(int i=0; i<internal.keyCount(); i++) {
				sb.append(internal.yearAtIndex(i));
				sb.append("|");
				sb.append(internal.keyAtIndex(i));
				sb.append("\n");
			}
			sb.append("</index>");
			System.out.println(sb.toString());
			for(int i=0; i<internal.childrenCount(); i++) {
				printSecondaryLibrary(internal.getChildrenAt(i));
			}
		}
	}

	public boolean overflow(ArrayList list) {
		return list.size() > 2*LibraryNode.order;
	}

}
// Extra functions if needed
