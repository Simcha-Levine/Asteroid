project('Astroid', 'cpp', version : '0.1', 
  default_options : ['warning_level=3', 'cpp_std=c++20'])

sfml = [dependency('sfml-graphics'),
 dependency('sfml-window'),
  dependency('sfml-system'),
  dependency('sfml-audio')]
box2d = dependency('box2d')

incdir = [include_directories('include')]


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

exe = executable('hello', src, install : true, dependencies : [sfml, box2d], include_directories : incdir)

test('basic', exe)