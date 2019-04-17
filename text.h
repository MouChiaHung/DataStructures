#ifndef _TEXT_H_
#define _TEXT_H_

class MyText {
//private:
	//friend class MyTextView;
protected:
	char	text[128];
	int		length;
public:
	int		arg; 
	void 	getText(char *dest);
	void 	setText(char *src);
	void 	showText();
	MyText(char *src);
	MyText();
	~MyText();
};

#endif