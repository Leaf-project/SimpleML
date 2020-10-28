std::string read_file(std::string filename) {
	std::string ret;
    std::string line;
    std::ifstream file(filename);
    while (std::getline(file, line)) ret += line+'\n';
    file.close();
	/*const char* name = filename.c_str();
	if (FILE *fp = fopen(name, "r")) {
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			ret.insert(ret.begin(), buf, buf + len);
		fclose(fp);
	}*/
	return ret;
};

std::vector<std::string> split(std::string text, char elm) {
	std::vector<std::string> ret = {""};
	int last = 0;
	for (char chr : text) {
		if (chr == elm) {
			ret.push_back("");
			last++;
		} else {
			ret[last] += chr;
		}
	}
	return ret;
};

std::string replace(std::string txt, std::string that, std::string by) {
	int pos=find(txt, that);
	while (pos != -1) {
		txt.erase(pos, pos+that.length());
		txt.insert(pos, by);
		pos = find(txt, that);
	}
	return txt;
};

std::vector<std::vector<std::string>> div_text(std::string text) {
	std::vector<std::string> brut;
	int last = -1;
	bool new_ = false;
	for (char chr : text) {
		if (chr == '[' or chr == ']') {
			brut.push_back("");
			last++;
		} else if (new_) {
			if (chr == '\n') {
				new_ = false;
			}
		} else {
			brut[last] += chr;
		}
	}
	std::vector<std::vector<std::string>> ret={std::vector<std::string>(), std::vector<std::string>()};
	int i=0;
	for (std::string elm : brut) {
		if (i%2==0) {
			ret[0].push_back(elm);
		} else {
			ret[1].push_back(elm);
		}
		i++;
	}
	return ret;
};

int find(std::string str, std::string patern) {
	int i,j;
	j = 0;
	for (i=0; i < str.length(); i++) {
		if (j == patern.length()) return i - j;
		if (str[i] == patern[j]) j++;
		else j = 0;
	}
	return -1;
};

template <class T> 
int in(T elm, std::vector<T> patern) {
	int lp = 0;
	for (T lp_elm : patern) {
		if (elm == lp_elm) return lp;
		lp++;
	}
	return -1;
};

template<class T> std::vector<int> sizes(Var<T>* var) {
	std::vector<int> ret;
	for (Array<T> arr: var->time) ret.push_back(arr.list_str.size());
	return ret;
};

template<class T> std::vector<int> lengths(Var<T>* var) {
	//max of lenght of one line in Array
	std::vector<int> ret;
	for (Array<T> arr: var->time) ret.push_back(arr.list_str[0].length());
	return ret;
};

template<class T> void ptr_arr(Array<T>* arr) {
	for (std::string line : arr->list_str) std::cout << line << '\n';
};

template<class T> void ptr_var(Var<T>* var) {
	int max_size = max<int>(sizes<T>(var));
	std::vector<int> _lenghts = lengths<T>(var);

	std::cout << debbug << "\033[33m";
	for (int i=0; i < var->time.size(); i++) {
		std::cout << "time:" << i;
		for (int _i=0; _i < _lenghts[i]-14; _i++) std::cout << ' ';
	}

	std::cout << "\033[0m\n";
	for (int i=0; i < max_size; i++) {
		std::cout << debbug;
		for (int _i=0; _i < var->time.size(); _i++) 
			if (var->time[_i].list_str.size() > i) 
				std::cout << var->time[_i].list_str[i] << " ";
		std::cout << std::endl;
	}
};

int max_length(std::vector<std::string> v) {
	int max = 0;
	for (std::string elm : v) if (elm.length() > max) max = elm.length();
	return max;
};

template<class T> void ptr_mem(Memory<T>* mem) {
	for (int i=0; i < mem->data.size(); i++) {
		std::cout << debbug << "\033[31m=========== \033[0mVar #" << i << " \033[31m===========\033[0m" << std::endl;
		ptr_var(&(mem->data[i]));
	}
	std::cout << debbug << "\033[31m=========== \033[36mCode \033[31m===========\033[0m" << std::endl;
	int max_length_line = max_length(mem->code.code);
	//ptr
	for (int i=0; i < mem->code.code.size(); i++) {
		//Print brut code
		std::cout << debbug << "\033[30m" << i << ">\033[0m " << mem->code.code[i];
		//Add spaces
		for (int j=0; j < max_length_line-(mem->code.code[i].length()); j++) std::cout << " ";
		std::cout << "    \033[0m(#";
		//Print colored code
		for (int _i=0; _i < mem->code.code[i].length(); _i++) {
			if (in<char>(mem->code.code[i][_i], operators) != -1) {
				std::cout << "\033[36m" << mem->code.code[i][_i] << "\033[0m)";
				if (_i != (mem->code.code[i].length()-1)) std::cout << "(#";
			} else {
				std::cout << mem->code.code[i][_i];
			}
		}
		std::cout << "\n";
	}
};

template<class T> void ptr_mdl(Model<T>* mdl) {
	std::cout << debbug << "Relativ : " << mdl->relativ << std::endl;
	for (int i=0; i < mdl->levels.size(); i++) {
		std::cout << debbug << "\033[31m|||||\033[32m Print Memory Block" << "\033[0m #" << i << " \033[31m|||||\033[0m\n";
		ptr_mem(&(mdl->levels[i]));
	};
};
