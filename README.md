# wrap_test

This is a simple demo showing how to use the option --wrap of ld linker.

--wrap symbol
    Use a wrapper function for symbol. 
    Any undefined reference to symbol will be resolved to __wrap_symbol. 
    Any undefined reference to __real_symbol will be resolved to symbol. 
    This can be used to provide a wrapper for a system function. 
    The wrapper function should be called __wrap_symbol. 
    If it wishes to call the system function, it should call __real_symbol.  
