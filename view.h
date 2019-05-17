#ifndef _VIEW_H_
#define _VIEW_H_

class MyView {
	
private:
	int id;
	friend class MyTextView;
protected:
	int left;
	int right;
	int top;
	int bottom;
public:
	int getLeft();
	int getRight();
	int getTop();
	int getBottom();
	void setLeft(int l);
	void setRight(int r);
	void setTop(int t);
	void setBottom(int b);
	//virtual void showPosition() = 0;
	void showPosition();
	void layout(int l, int r, int t, int b);
	MyView(int l, int r, int t, int b);
	~MyView();
	virtual void onLayout(int changed, int l, int r, int t, int b) = 0;
	//virtual void onLayout(int changed, int l, int r, int t, int b) {};
};

#endif