import { GLib } from '@girs/glib-2.0';

export const env = {};

export const platform = 'linux'; // TODO: GLib.get_os_info('ID');

export const arch = 'x64'; // TODO: GLib.get_ar();

export const report = {
  getReport: () => ({ header: {} }),
};

export default {
  platform,
  arch,
  report,
};
