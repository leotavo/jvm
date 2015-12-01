// Tconst_Tstore.java


public	class Tconst_Tstore{
	public	static	void	main(String args[]){
		iconst();
		lconst();
		fconst();
		dconst();
		aconst();
		istore();
		lstore012();
		lstore3();
		fstore();
		dstore012();
		dstore3();
		astore();
		
	}
	
	static  void	iconst(){
		int	a = -1;
		int	b = 0;
		int	c = 1;
		int	d = 2;
		int	e = 3;
		int	f = 4;
		int	g = 5;
	}
	
	static  void	lconst(){
		long	a = 0;
		long	b = 1;
	}
	
	static  void	fconst(){
		float	a = 0;
		float	b = 1;
		float	c = 2;
	
	}
	
	static  void	dconst(){
		double	a = 0;
		double	b = 1;
	}
	
	static  void	aconst(){
		String	a = null;
	}
	
	static	void	istore(){
		int	a = 0;
		int	b = 1;
		int	c = 2;
		int	d = 3;
		int	e = 4;
	}
	
	static	void	lstore012(){
		long	a = 0;
		long	b = 1;
		long	c = 2;
	}
	
	static	void	lstore3(){
		int	a = 0;
		int	b = 1;
		int	c = 1;
		long	d = 2;
	}
	
	static	void	fstore(){
		float	a = 0;
		float	b = 1;
		float	c = 2;
		float	d = 3;
		float	e = 4;
	}
	
	static	void	dstore012(){
		double	a = 0;
		double	b = 1;
		double	c = 2;
	}
	
	static	void	dstore3(){
		int	a = 0;
		int	b = 1;
		int	c = 1;
		double	d = 2;
	}
	
	static	void	astore(){
		String	a = null;
		String	b = null;
		String	c = null;
		String	d = null;
		String	e = null;
	}
}
