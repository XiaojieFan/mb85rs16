from building import *
Import('rtconfig')

src   = []
cwd   = GetCurrentDir()

# add mb85rs16 src files.
if GetDepend('PKG_USING_MB85RS16'):
src += Glob('src/mb85rs16.c')
if GetDepend('PKG_USING_MB85RS16_SAMPLE'):
src += Glob('examples/mb85rs16_sample.c')
# add mb85rs16 include path.
path  = [cwd + '/inc']

# add src and include to group.
group = DefineGroup('mb85rs16', src, depend = ['PKG_USING_MB85RS16'], CPPPATH = path)


Return('group')

