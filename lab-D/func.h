int read_input_from_file(const char* filename, char* num1_str, long long* num2);
void write_output_to_file(const char* filename, int digits[], int n, char* result_oper, int target, int found);
double solve_equation(int digits[],char oper[],int n);
int digits_split(const char* num_str,int* digits);
int find_equation(int* digits,int n,int depth,char*result_oper,char* current_oper,char* operations,int target);