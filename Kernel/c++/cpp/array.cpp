template<class T> T add(T a, T b) {return a + b;};
template<class T> T sub(T a, T b) {return a - b;};
template<class T> T mul(T a, T b) {return a * b;};
template<class T> T div(T a, T b) {return a / b;};
template<class T> T _pow(T a, T b) {return pow(a, b);};
template<class T> T add_lst(std::vector<T> lst) {T ret;for(T _ : lst)ret+=_;return ret;};
template<class T> T sub_lst(std::vector<T> lst) {T ret;for(T _ : lst)ret-=_;return ret;};
template<class T> T mul_lst(std::vector<T> lst) {T ret=1;for(T _ : lst)ret*=_;return ret;};
template<class T> T div_lst(std::vector<T> lst) {T ret=1;for(T _ : lst)ret/=_;return ret;};
template<class T> T pow_lst(std::vector<T> lst) {T ret=0;for(T _ : lst)ret=pow(ret,_);return ret;};
//
template<class T> int Array<T>::get_real_pos(std::vector<int> pos) {
	int pos_=0;
	for (int i=0; i < pos.size(); i++) pos_ += (real_sizes[i]*pos[i]);
	return pos_;
};
template<class T> void Array<T>::compute_real_sizes() {
	real_sizes.clear();
	real_sizes.push_back(1);
	for (int i=shape.size()-1; i > 0; i--)
		real_sizes.insert(real_sizes.begin(), shape[i]*real_sizes[0]);
};
template<class T> void Array<T>::set_eq(Array<T> b) {
	data.clear();
	for (int i=0; i < b.length; i++) data.push_back(b.get_data(i));
	shape = b.shape;
	compute_real_sizes();
	deep = b.deep;
	length = b.length;
	update_str();
};
//Controle functions
template<class T> void Array<T>::insert(int pos, T value){data.insert(pos, value);length++;update_str();};
template<class T> void Array<T>::set(int i, T value){this->data[i] = value;update_str();};
template<class T> void Array<T>::push_back(T value){data.push_back(value);length++;update_str();};
template<class T> T& Array<T>::get_data(int i) {return data[i];};
template<class T> T& Array<T>::operator[](std::vector<int> pos) {return data[get_real_pos(pos)];};
template<class T> T& Array<T>::get(std::vector<int> pos) {return data[get_real_pos(pos)];};
template<class T> void Array<T>::set_data(std::vector<T> data) {for (int i=0; i < data.size(); i++) set(i, data[i]);};
//Debbug Function
template<class T> void Array<T>::update_str() {
	list_str.clear();
	//Check if lenght of data correspond to shape to avoid illegal storage
	if (length != mul_lst<int>(shape) and length != 0) {
		std::cerr << debbug << "\033[31m\033[1m/!\\ Lenght of data not corresponding to shape /!\\\n";
		std::cerr << debbug << "\033[31m\033[1mShape : (";
		for (int elm : shape) std::cerr << elm << ",";
		std::cerr << ") and length:" << length << "; mul:" << mul_lst<int>(shape) << "\n";
		std::cerr << debbug << "\033[31m\033[1mFlat data : [";
		for (T _ : data) std::cerr << _ << ",";
		std::cerr << "]\033[0m\n";
	} else if (deep == 1) {
		// 1D
		list_str.push_back("");
		list_str[0] += "[ \033[32m";
		for (T elm : data) list_str[0] += std::to_string(elm) +" ";
		list_str[0] += "\033[0m]";
	} else if (deep == 2) {
		// 2D
		int lp=0;
		std::vector<int> pos = {0,0}; int x,y;x=0;y=0;
		for (y=0; y < shape[0]; y++) {
			list_str.push_back("");
			list_str[lp] += "|\033[32m";
			for (x=0; x < shape[1]-1; x++) {
				pos[0] = y; pos[1] = x;
				list_str[lp] += std::to_string(data[get_real_pos(pos)]) + " ";
			}
			pos[0] = y; pos[1] = x;
			list_str[lp] += std::to_string(data[get_real_pos(pos)]) + "\033[0m";
			lp++;
		}
	} else {
		// 3D+
	}
	/////Add spaces to make equilibre
	//Find max
	int max=0;
	for (std::string elm : list_str) if (elm.length() > max) max = elm.length();
	//Add Spaces
	int size;
	for (int i=0; i < list_str.size(); i++) {
		size = list_str[i].length();
		for (int _i=0; _i < (max-size); _i++) list_str[i]+=" ";
		list_str[i] += "|";
	}
};
//Operator
template<class T> Array<T> Array<T>::lin_ope(Array<T>* b, T(*ope)(T,T)) {
	if (length == b->length) { // len == len
		Array<T> ret({}, this->shape);
		for (int i=0; i < this->length; i++) ret.push_back(ope(this->data[i], b->get_data(i)));
		ret.length = this->length;
		return ret;
	} else if (this->length == 1) { // len == 1
		Array<T> ret({}, b->shape);
		for (int i=0; i < b->length; i++) ret.push_back(ope(this->data[0], b->get_data(i)));
		ret.length = b->length;
		return ret;
	} else if (b->length == 1) { // 1 == len
		Array<T> ret({}, this->shape);
		for (int i=0; i < this->length; i++) ret.push_back(ope(this->data[i], b->get_data(0)));
		ret.length = this->length;
		return ret;
	} else {
		std::cerr << "(" << ope <<") Lenght Error " << this->length << " != " << b->length << std::endl;
	}
};
//Magic Function
template<class T> Array<T> Array<T>::operator+(const Array<T> &b) {return lin_ope(*b, &add);};
template<class T> Array<T> Array<T>::operator-(const Array<T> &b) {return lin_ope(*b, &sub);};
template<class T> Array<T> Array<T>::operator*(const Array<T> &b) {return lin_ope(*b, &mul);};
template<class T> Array<T> Array<T>::operator/(const Array<T> &b) {return lin_ope(*b, &div);};
template<class T> Array<T> Array<T>::operator^(const Array<T> &b) {return lin_ope(*b, &_pow);};
template<class T> void Array<T>::operator=(const Array<T> &b) {set_eq(b);};
template<class T> void Array<T>::operator+=(const Array<T> &b) {set_eq(lin_ope(*b, &add));};
template<class T> void Array<T>::operator-=(const Array<T> &b) {set_eq(lin_ope(*b, &sub));};
template<class T> void Array<T>::operator*=(const Array<T> &b) {set_eq(lin_ope(*b, &mul));};
template<class T> void Array<T>::operator/=(const Array<T> &b) {set_eq(lin_ope(*b, &div));};
template<class T> void Array<T>::operator^=(const Array<T> &b) {set_eq(lin_ope(*b, &_pow));};
//Spetial function
template<class T> Array<T> Array<T>::dot(Array<T> *b) {
	if (this->deep == 2 and b->deep == 2) {
		//Dot classic
		if (this->shape[1] == b->shape[0]) {
			Array<T> ret({}, {this->shape[0], b->shape[1]});
			int pos=0;
			std::vector<int> pa={0,0}, pb={0,0};
			for (int row=0; row < this->shape[0]; row++) { // Ligne
				for (int col=0; col < b->shape[1]; col++) { // Column
					ret.push_back(T(0));pos = ret.length;ret.length++;
					for (int k=0; k < b->shape[0]; k++) {
						pa[0]=row;pa[1]=k;
						pb[0]=k;pb[1]=col;
						ret.set(pos, ret.get_data(pos) + data[this->get_real_pos(pa)]*b->get(pb));
					}
				}
			}
			return ret;
		} else {
			std::cerr << "[Error] (@) Shape invalid in ("
					<< this->shape[0] << ", " << this->shape[1] << ") ("
					<< b->shape[0] << ", " << b->shape[1] << ") "
					<< this->shape[1] << "!=" << b->shape[0] << "\n";
			std::exit(1); // avoid std::badalloc
		}
	} else if (this->deep == 1 and b->deep == 2) {
		if (this->shape[0] == b->shape[0]) { // (k) and (m,n)  k==m
			Array<T> ret({}, {b->shape[1]});
			int pos=0;
			std::vector<int> pa={0}, pb={0,0};
			for (int col=0; col < b->shape[1]; col++) { // Column
				ret.push_back(T(0));pos=ret.length;ret.length++;
				for (int k=0; k < b->shape[0]; k++) {
					pa[0]=k;
					pb[0]=k;pb[1]=col;
					ret.set(pos, ret.get_data(pos) + data[this->get_real_pos(pa)]*b->get(pb));
				}
			}
			return ret;
		} else {
			std::cerr << "[Error] (@) Shape invalid in a@b ("
					<< this->shape[0] << ") and ("
					<< b->shape[0] << "," << b->shape[1] << ") "
					<< this->shape[0] << "!=" << b->shape[0] << "\n";
		}
	} else if (this->deep == 2 and b->deep == 1) {
		if (b->shape[0] == this->shape[0]) { // (k) and (m,n)  k==m
			Array<T> ret({}, {this->shape[1]});
			int pos=0;
			std::vector<int> pa={0,0}, pb={0};
			for (int col=0; col < this->shape[1]; col++) { // Column
				ret.push_back(T(0));pos=ret.length;ret.length++;
				for (int k=0; k < this->shape[0]; k++) {
					pa[0]=k;pa[1]=col;
					pb[0]=k;
					ret.set(pos, ret.get_data(pos) + data[this->get_real_pos(pa)]*b->get(pb));
				}
			}
			return ret;
		} else {
			std::cerr << "[Error] (@) Shape invalid in a@b ("
					<< this->shape[0] << "," << this->shape[1] << ") and ("
					<< b->shape[0] << ") "
					<< this->shape[0] << "!=" << b->shape[0] << "\n";
		}
	} else {
		std::cerr << "[Error] /!\\ Error Dot Product /!\\\n";
		std::exit(1); // avoid std::badalloc
	}
};
//Char operations
template<class T> void Array<T>::operation_char(Array<T>* b, char chr) {
	switch (chr) {
		case '+': set_eq(lin_ope(b, &add));break;
		case '-': set_eq(lin_ope(b, &sub));break;
		case '*': set_eq(lin_ope(b, &mul));break;
		case '/': set_eq(lin_ope(b, &div));break;
		case '^': set_eq(lin_ope(b, &_pow));break;
		case '@': set_eq(dot(b));break;
		case '=': set_eq(*b);break;
		default:
			std::cerr << "Operator (" << chr << ") not understanded.\n";
			break;
	}
};
//Init
template<class T> Array<T>::Array(std::vector<T> arr, std::vector<int> dim) {
	data = arr;
	shape = dim;
	compute_real_sizes();
	deep = dim.size();
	length = arr.size();
	update_str();
};