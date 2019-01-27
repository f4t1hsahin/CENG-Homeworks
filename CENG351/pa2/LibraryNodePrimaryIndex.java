import java.util.*;

public class LibraryNodePrimaryIndex extends LibraryNode
{
	private ArrayList<Integer> keys;
	private ArrayList<LibraryNode> children;

	public LibraryNodePrimaryIndex(LibraryNode parent)
	{
		super(parent);
		keys = new ArrayList<Integer>();
		children = new ArrayList<LibraryNode>();
		this.type = LibraryNodeType.Internal;
	}

	public LibraryNodePrimaryIndex(LibraryNode parent, ArrayList<Integer> keys, ArrayList<LibraryNode> children)
	{
		super(parent);
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

	// Extra functions if needed

	public void addChild(LibraryNode child) {
		children.add(child);
	}

	public void addKey(Integer key) {
		if(key == -1) {
			return;
		}
		keys.add(key);
	}

	public void addPair(Integer key, LibraryNode child) {
		int index = Collections.binarySearch(keys, key);
		index = index > 0 ? index : -index - 1;
		if(key != -1 && !keys.contains(key)) {
			keys.add(index, key);
		}
		if(index >= children.size() || index < 0) {
			children.add(child);
		}else {
			children.add(index + 1, child);
		}
	}

	public int childrenCount() {
		return children.size();
	}

	public ArrayList<Integer> getKeys() {
		return keys;
	}

	public boolean overflow(int order) {
		return this.keyCount() > 2*order;
	}

}
