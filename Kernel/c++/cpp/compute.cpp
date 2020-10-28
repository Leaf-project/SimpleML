/*
Struct:nb,op
nb - pos of var in memory.
op - operator to apply to target : target = target op mem[nb]
example: 2|0=1* => $(2) = $(0) * $(1)
*/

template<class T>
int _exec(Memory<T>* mem, int fid, int inpid, int time, bool ptr_debbug) {
	if (ptr_debbug) std::cout << computing << "[Exec func] id:" << fid << " line:" << mem->code.fnlines[fid]+1 << "\n"; //+1 because in sublime text line start form 1
	std::string number;
	char chr;
	int target;
	for (int line=(mem->code.fnlines[fid])+1; line < mem->code.code.size(); line++) {
		for (int i=0; i < mem->code.code[line].length(); i++) {
			switch (chr = mem->code.code[line][i]) {
				case '+':case '-':case '*': case '/': case '^': case '@': case '=':
					if (ptr_debbug) std::cout << computing << "[Compute steps] : #" << target << " #" << number << chr << " line:" << line+1 << " i:" << i <<"\n";
					mem->data[target].time[time].operation_char(
						&mem->data[std::stoi(number)].time[time], chr);
					number = "";
					break;
				case ')':
					if (ptr_debbug) std::cout << computing << "[Compute steps] : #" << target << " #" << number << chr << " line:" << line+1 << " i:" << i <<"\n";
					mem->data[target].time[time].operation_char(
						&(mem->data[_exec(mem, std::stoi(number), target, time, ptr_debbug)].time[time]),
						'=');
					number.clear();
					break;
				case '|':
					target = std::stoi(number);
					number.clear();
					break;
				case ':':
					std::cerr << "\033[31mcompute->_exec->(:)  cannot be ':' in func declaration line:" << line << " i:" << i << "\n";
					std::exit(1);
					break;
				case '#':
					return std::stoi(number);
				default:
					number += chr;
					break;
			}
		}
	}
}; // return id of return (pos)


template<class T>
void compute(Memory<T> * mem, int time, bool ptr_debbug) {
	_exec(mem, mem->code.main, mem->code.argsid[mem->code.main],time, ptr_debbug);
};
