#include <unistd.h>
#include <cstring>
#include <cstdlib>

class N{
	public:
		int (N::*func)(N &);
		char str[100];
		int nb;
		
	N(int val){
		this->nb = val;
		this->func = &N::operator+;
	}

	void setAnnotation(char *val){
		memcpy(this->str, val, strlen(val));
	}

	virtual int operator+(N &obj){
		return this->nb + obj.nb; 
	}

	virtual int operator-(N &obj){
		return this->nb - obj.nb;
	}
};

int main(int argc,char **argv){
	if (argc < 1)
		exit(1);

	N *a = new N(5);
	N *b = new N(6);

	a->setAnnotation(argv[1]);
	return (b->*(b->func))(*a);
}
