#!/usr/bin/env python

# System modules
import sys,os
import unittest
import signal
import threading, time
import gtk

# TREX modules
from TREX import *
from TREX.core import *
from TREX.widgets_gtk import *

def main():
  # Process cli arguments
  if len(sys.argv) > 1:
    log_path = sys.argv[1]
  else:
    log_path = "."

  # Window configuration for a window that should not be allowed to be closed
  WINDOW_FUNCTIONS = gtk.gdk.FUNC_MOVE | gtk.gdk.FUNC_RESIZE | gtk.gdk.FUNC_MINIMIZE | gtk.gdk.FUNC_MAXIMIZE;

  # Initialize gtk multithread support
  gtk.gdk.threads_init()

  # Create db reader window
  db_reader_window = DbReaderWindow(log_path=log_path)
  db_reader_window.w.connect("destroy",gtk.main_quit)

  # Create timelien viewer window
  timeline_window = TimelineWindow()
  timeline_window.w.window.set_functions(WINDOW_FUNCTIONS)
  db_reader_window.register_listener(timeline_window.set_db_cores)

  ############################################################

  # Create token network graph generator
  token_network = TokenNetwork()

  # Create token network window
  token_network_window = TokenNetworkWindow(token_network)
  token_network_window.window.set_functions(WINDOW_FUNCTIONS)
  token_network_window.register_listener(PropertyWindowFactory)

  # Create token network filter window
  token_network_filter = TokenNetworkFilter(token_network)
  token_network_filter_window = TokenNetworkFilterWindow(token_network_filter)
  token_network_filter_window.w.window.set_functions(WINDOW_FUNCTIONS)

  # Create conflict list window
  def SetSourceFile(tick, reactor):
    db_reader_window.tick_entry.set_text(db_reader_window.format_tick(tick))
    db_reader_window.go_but.emit("clicked")
    
    timeline_window.set_visible_reactor(reactor)

  conflict_list_window = ConflictListWindow()
  conflict_list_window.register_activate_callback(SetSourceFile)
  db_reader_window.register_listener(conflict_list_window.set_db_cores)

  def SpawnPropertyWindow(db_core, token):
    PropertyWindowFactory(db_core.assembly, db_core.assembly.tokens[token.key])

  def HilightInTokenNetwork(db_core,token):
    # Set assembly in token network
    token_network.set_db_cores({db_core.reactor_name : db_core},db_core.reactor_name)
    
    # Set the filter for the token key
    token_network_filter_window.filter_entry.set_text("^"+str(token.key)+"$")
    token_network_filter_window.rep_but.emit("clicked")
    token_network_filter_window.use_regex_check.set_active(True)
    token_network_filter_window.use_regex_check.emit("toggled")
    token_network_window.present()

  # Register context extensions
  timeline_window.register_context_extension("View token properties...",SpawnPropertyWindow)
  timeline_window.register_context_extension("Hilight in token network...",HilightInTokenNetwork)
  timeline_window.register_double_click_callback(HilightInTokenNetwork)

  # Bring the db reader forward
  db_reader_window.w.present()

  # Set up signal handler
  signal.signal(signal.SIGINT, signal.SIG_DFL) 

  gtk.main()

if __name__ == '__main__':
  main()
