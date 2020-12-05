from distutils.core import setup, Extension

module = Extension('myarithmetic', sources=['wrapper/myarithmetic.c'])

setup(name='packagename',
      version='1.0',
      description='description',
      ext_modules=[module])
