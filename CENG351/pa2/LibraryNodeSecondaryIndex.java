import java.util.*;

public class LibraryNodeSecondaryIndex extends LibraryNode
{
	private ArrayList<Integer> keys;
	private ArrayList<Integer> years;
	private ArrayList<LibraryNode> children;

	public LibraryNodeSecondaryIndex(LibraryNode parent)
	{
		super(parent);
		keys = new ArrayList<Integer>();
		years = new ArrayList<Integer>();
		children = new ArrayList<LibraryNode>();
		this.type = LibraryNodeType.Internal;
	}

	public LibraryNodeSecondaryIndex(LibraryNode parent, ArrayList<Integer> years, ArrayList<Integer> keys, ArrayList<LibraryNode> children)
	{
		super(parent);
		this.years = years;
		this.keys = keys;
		this.children = children;
		this.type = LibraryNodeType.Internal;
	}

	// GUI Methods - Do not modify
	public ArrayList<LibraryNode> getAllChildren()
	{
		return this.children;
	}

	public LibraryNode getChildrenAt(Integer index) {

		return this.children.get(index);
	}

	public Integer keyCount()
	{
		return this.keys.size();
	}
	public Integer keyAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.keys.get(index);
		}
	}

	public Integer yearAtIndex(Integer index)
	{
		if(index >= this.keyCount() || index < 0)
		{
			return -1;
		}
		else
		{
			return this.years.get(index);
		}
	}

	public Integer childrenCount() {
		return this.children.size();
	}

	public ArrayList<Integer> getYears() {
		return this.years;
	}

	public ArrayList<Integer> getKeys() {
		return this.keys;
	}

	public void addChild(LibraryNode child) {
		children.add(child);
	}

	public void addKey(Integer key) {
		if(key == -1) {
			return;
		}
		keys.add(key);
	}

	public void addYear(Integer year) {
		if(year == -1) {
			return;
		}
		years.add(year);
	}

	public void add(Integer year, Integer key, LibraryNode child) {
		int index = search(year, key);
		years.add(index, year);
		keys.add(index, key);
		children.add(index + 1, child);
	}

	public boolean overflow(int order) {
		return this.keys.size() > 2*order;
	}

	public Integer search(Integer year, Integer key) {
		int index = Collections.binarySearch(years, year);
		if(index < 0) {
			return -index - 1;
		}else {
			ArrayList<Integer> temp = new ArrayList<>();
			for(int i = index; i<keys.size(); i++) {
				if(!years.get(i).equals(year)) {
					break;
				}else {
					temp.add(keys.get(i));
				}
			}

			int insert = Collections.binarySearch(temp, key);
			return index + (insert >= 0 ? insert : -insert - 1);
		}
	}



	// Extra functions if needed

}
