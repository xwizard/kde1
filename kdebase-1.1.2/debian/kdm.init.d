#!/bin/sh
# /etc/init.d/kdm: start or stop the X display manager

set -e

PATH=/bin:/usr/bin:/sbin:/usr/sbin
DAEMON=/usr/bin/kdm
PIDFILE=/var/run/kdm.pid

test -x $DAEMON || exit 0

if grep -qs ^check-local-xserver /etc/X11/kdm/kdm.options; then
  if head -1 /etc/X11/Xserver 2> /dev/null | grep -q Xsun; then
    # the Xsun X servers do not use XF86Config
    CHECK_LOCAL_XSERVER=
  else
    CHECK_LOCAL_XSERVER=yes
  fi
fi

case "$1" in
  start)
    if [ "$CHECK_LOCAL_XSERVER" ]; then
      problem=yes
      echo -n "Checking for valid XFree86 server configuration..."
      if [ -e /etc/X11/XF86Config ]; then
        if [ -x /usr/sbin/parse-xf86config ]; then
          if parse-xf86config --quiet --nowarning --noadvisory /etc/X11/XF86Config; then
            problem=
          else
            echo "error in configuration file."
          fi
        else
          echo "unable to check."
        fi
      else
        echo "file not found."
      fi
      if [ "$problem" ]; then
        echo "Not starting X display manager."
        exit 1
      else
        echo "done."
      fi
    fi
    echo -n "Starting X display manager: kdm"
    start-stop-daemon --start --quiet --pid $PIDFILE --exec $DAEMON || echo -n " already running"
    echo "."
  ;;

  restart)
    /etc/init.d/kdm stop
    /etc/init.d/kdm start
  ;;

  reload)
    echo -n "Reloading X display manager configuration..."
    if start-stop-daemon --stop --signal 1 --quiet --pid $PIDFILE --exec $DAEMON; then
      echo "done."
    else
      echo "kdm not running."
    fi
  ;;

  force-reload)
    /etc/init.d/kdm reload
  ;;

  stop)
    echo -n "Stopping X display manager: kdm"
    start-stop-daemon --stop --quiet --pid $PIDFILE --exec $DAEMON || echo -n " not running"
    echo "."
  ;;

  *)
    echo "Usage: /etc/init.d/kdm {start|stop|restart|reload|force-reload}"
    exit 1
    ;;
esac

exit 0
