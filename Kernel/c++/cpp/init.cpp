std::string del_com(std::string text) {
	std::string ret;
	bool back_slash,read;
	read = true;
	//Del ///
	for (int i=0; i < text.length(); i++) {
		if (text[i] == '\n') {
			if (read or ret[ret.length()-1] != '\n') ret += '\n';
			read = true;
		} else if (read) {
			if (text[i] == ' ' or (text[i]=='/'&&text[i+1]=='/') or text[i]=='\t') {
				read = false;
			} else {
				ret += text[i];
			}
		}
	}
	if (ret[0]=='\n') ret.erase(0,1);
	return ret;
};

template<class T> Memory<T> load_mem(std::string file, std::string main_pos) {
	Memory<T> ret;
	ret.code.code = split(del_com(read_file(file)), '\n');
	ret.code.main = std::stoi(main_pos);
	//Get funcs
	std::string number = "";
	for (int line=0; line < ret.code.code.size(); line++) {
		for (int i=0; i < ret.code.code[line].length(); i++) {
			switch (ret.code.code[line][i]) {
				case ':':
					ret.code.fnlines.push_back(line);
					ret.code.argsid.push_back(std::stoi(number));
					number = "";
					break;
				default:
					number += ret.code.code[line][i];
					break;
			}
		}
		number = "";
	}
	return ret;
};

template<class T> std::vector<T> str_to_list(std::string text) {
	// no ',' at end
	std::vector<T> ret;
	std::string number;

	for (char chr : text) {
		switch (chr) {
			case ',':
				ret.push_back(std::stod(number));
				number = "";
				break;
			default:
				number += chr;
				break;
		}
	}
	if (number.length() > 0) ret.push_back(std::stod(number));
	return ret;
};

template<class T> void init_mem(Memory<T>* mem, std::string file, bool add_new_arr) {
	std::string text = read_file(file);
	std::string tmp;
	std::vector<T> values;
	int lp=0;
	Var<T> var;
	var.time.push_back(Array<T>({}, {0}));
	for (char chr : text) {
		switch (chr) {
			case '/':
				if (add_new_arr) {
					var.time[0] = Array<T>(values, str_to_list<int>(tmp));
					mem->data.push_back(var);
				} else {
					mem->data[lp].time[0] = Array<T>(values, str_to_list<int>(tmp));
					lp++;
				}
				tmp="";
				break;
			case ':':
				//convert tmp to list of doubles
				values = str_to_list<T>(tmp);
				tmp="";
				break;
			default:
				tmp += chr;
				break;
		}
	}
	if (tmp.length() > 0) {
		if (add_new_arr) {
			var.time[0] = Array<T>(values, str_to_list<int>(tmp));
			mem->data.push_back(var);
		} else {
			mem->data[lp].time[0] = Array<T>(values, str_to_list<int>(tmp));
			lp++;
		}
	}
};

//Load Model from file
template<class T> Model<T> load_model(std::string file) {
	Model<T> ret;
	std::vector<std::string> tmp;
	// code_file:init_vars_file
	std::vector<std::string> lines = split(del_com(read_file(file)), '\n');
	ret.relativ = std::stoi(lines[0]);
	for (int i=1; i < lines.size()-1; i++) {
		tmp = split(lines[i], ';');
        ret.levels.push_back(load_mem<T>(tmp[0], tmp[1]));
		init_mem<T>(&(ret.levels[ret.levels.size()-1]), tmp[2], true);
	}

	return ret;
};

template<class T> void add_number(Memory<T>* mem, T number) {
	Var<T> tmp;
	tmp.time.push_back(Array<T>({number}, {1}));
	mem->data.push_back(tmp);
};
