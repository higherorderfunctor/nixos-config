import { GLib } from '@girs/glib-2.0';

export const env = {};

export const platform = 'linux'; // TODO: GLib.get_os_info('ID');

export const arch = 'x64'; // TODO: GLib.get_ar();

const decoder = new TextDecoder('utf-8');

// TODO: port to effect
const getGlibcVersion = () => {
  // Execute the `ldd` command which outputs the glibc version among other things
  const [ok, out, err, exit] = GLib.spawn_command_line_sync('ldd --version');

  if (ok && exit === 0) {
    // Convert the output to a string
    const output = decoder.decode(out);

    // Extract the first line which contains the glibc version
    const firstLine = output.split('\n', 1)[0];

    // Extract the version number
    const match = firstLine.match(/(\d+\.\d+)/);
    if (match) {
      return match[1]; // Return the version number as a string
    }
  }

  return null; // Return null if the version couldn't be determined
};

// https://nodejs.org/api/report.html
export const report = {
  getReport: () => ({
    header: {
      glibcVersionRuntime: getGlibcVersion(),
    },
  }),
};

export default {
  platform,
  arch,
  report,
};
