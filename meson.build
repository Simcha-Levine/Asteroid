project('Asteroid', 'cpp', version : '0.1', 
  default_options : ['warning_level=3', 'cpp_std=c++20'])

sfml = [dependency('sfml-graphics'),
 dependency('sfml-window'),
  dependency('sfml-system'),
  dependency('sfml-audio')]
box2d = dependency('box2d')


# box2d_dir = '/home/simcha-levine/vcpkg/packages/box2d_x64-linux/lib'
incdir = [include_directories('include')]


# cc = meson.get_compiler('cpp')
# bin_dep = declare_dependency(
#   dependencies : cc.find_library('libbox2d', dirs : box2d_dir))

# box2d = subproject('bob').get_variable('bin_dep')


src = [
  'main.cpp',
  'Game.cpp',
  'Player.cpp',
  'VectorConverter.cpp',
  'GShip.cpp',
  'GJet.cpp',
  'GameAction.cpp',
  'Barrier.cpp',
  'ContactListener.cpp',
  'Astroid.cpp',
  'Bullet.cpp',
  'SoundMaker.cpp',
  'UiStats.cpp'
  ]

exe = executable('asteroid', src, install : true, dependencies : [sfml, box2d], include_directories : incdir)

test('basic', exe)