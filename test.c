void func(int* a){
	*a = 20;
}
int main(int argc, char const *argv[])
{
	int* a;
	printf("%d\n", a);
	func(&a);
	printf("%d\n", a);
	
	/* code */
	return 0;
}