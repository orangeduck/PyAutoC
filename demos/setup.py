from distutils.core import setup, Extension

pyautoc_files = ['src/PyAutoC.c', 'src/PyAutoConvert.c', 'src/PyAutoFunction.c', 'src/PyAutoStruct.c', 'src/PyAutoType.c']

module1 = Extension('pyautoc_demo', sources = ['demos/demo_mod.c'] + pyautoc_files, 
                                    include_dirs = ['./include'], library_dirs = ["./Python27/libs"], 
                                    extra_compile_args=["--std=gnu99"])

setup(name = 'pyautoc_demo',
      version = '1.0',
      description = 'This is a demo package for pyautoc_demo',
      author = 'Daniel Holden',
      author_email = 'contact@theorangeduck.com',
      ext_modules = [module1])
       