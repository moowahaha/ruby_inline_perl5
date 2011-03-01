#include <ruby.h>
#include <EXTERN.h>
#include <perl.h>

VALUE rb_cPerlWrapper = Qnil;

VALUE stop_perl(PerlInterpreter *perl) {
    perl_destruct(perl);
    perl_free(perl);
    PERL_SYS_TERM();
}

VALUE start_perl(VALUE klass) {
    int argc;
    char **argv;
    char **env;

    static PerlInterpreter *perl;
	PERL_SYS_INIT3(&argc,&argv,&env);

    perl = perl_alloc();
    perl_construct(perl);

	PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

    return Data_Wrap_Struct(klass, 0, stop_perl, perl);
}

VALUE rb_initialize(VALUE self, VALUE perl_string) {
}

VALUE rb_run(VALUE self) {
}

void Init_perl_wrapper() {
    VALUE rb_cInlinePerl5 = rb_define_class("InlinePerl5", rb_cObject);
    rb_cPerlWrapper = rb_define_class_under(rb_cInlinePerl5, "Wrapper", rb_cObject);

    rb_define_method(rb_cPerlWrapper, "initialize", &rb_initialize, 1);
    rb_define_method(rb_cPerlWrapper, "run", &rb_run, 0);
    rb_define_alloc_func(rb_cPerlWrapper, start_perl);
}
