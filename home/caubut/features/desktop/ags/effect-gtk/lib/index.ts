import '@girs/gjs';
import '@girs/gtk-4.0';

import Gtk from 'gi://Gtk?version=4.0';

import GLib from 'gi://GLib';
import GObject from 'gi://GObject';

const loop = GLib.MainLoop.new(null, false);

class App extends Gtk.Application {
  vfunc_activate() {
    const window = new Gtk.ApplicationWindow({ application: this });
    const label = new Gtk.Label({ label: 'Hello World!' });
    window.child = label;
    window.connect('close-request', () => loop.quit());
    window.present();
  }
}

export const FbrApplication = GObject.registerClass(
  {
    GTypeName: 'FbrApplication',
  },
  App,
);

export function main() {
  return new FbrApplication({ application_id: 'egs' }).run(null);
}

const app = new App();
app.run(null);

loop.run();
