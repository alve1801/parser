#ifndef LOADER
#define LOADER
struct Loader{
	FILE*f;char a;
	Loader(const char*filename){/*printf("open %s\n",filename);*/f=fopen(filename,"r");}
	void close(){if(f)fclose(f);/*printf("file closed\n");*/} // not in a destructor, bc sometimes we dont wanna close it
	void rew(){fseek(f,-1,SEEK_CUR);} // ideally, we wont ever need this XXX and get
	char get(){return a=getc(f);}
	void newl(){while(a!=10)get();}

	char white(){
		get(); // XXX omit this?
		while(a==9||a==10||a==32)get();
		return a;
	}

	float parseint(){
		float ret=0,prec=.1;bool inv=0;
		white();

		if(a=='-'){inv=1;get();}
		while('0'<=a&&a<='9'){
			ret=ret*10+a-'0';
			get();
		}

		if(a=='.'){
			get();
			while('0'<=a&&a<='9'){
				ret+=(a-'0')*prec;
				prec/=10;
				get();
			}
		}

		//if(a=='e')ret=ret*powf(10,parseint());

		if(inv)ret*=-1;

		return ret;
	}

	char*parsestr(){
		char*str=(char*)malloc(100),sp=0; // vector instead of char[] would allow us arbitrarily long strings
		white();
		while('a'<=a&&a<='z' || '0'<=a&&a<='9' || a=='_'){ // XXX
			str[sp++]=a;
			get();
		}
		str[sp]=0;
		return str;
	}
};
#endif

// consider making it able to load from string or smth, so we can hardcode values?
