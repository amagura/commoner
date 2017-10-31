#|
Copyright (C) 2015, 2016, 2017 Alexej G. Magura

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
|#
(declaim (inline argc*))

(defun argc* ()
  "returns the number of arguments available to the current program"
  (or #+clisp         (length *args*)
      #+sbcl          (length *posix-argv*)
      #+abcl          (length *command-line-argument-list*)
      #+(or mkcl ecl) (si:argc)
      nil))

(defun argv* (&optional .nth.)
  "returns either a list of args or a particular arg if .nth. is not null.
   calls `error' if something goes wrong."
  (if (null .nth.)
      (or #+clisp *args*
          #+sbcl  *posix-argv*
          #+abcl  *command-line-argument-list*
          nil)
      (if (< .nth. (argc*)) ; make sure that we have enough args to get .nth. arg
          (or #+clisp (nth .nth. *args*)
              #+sbcl  (nth .nth. *posix-argv*)
              #+abcl  (nth .nth. *command-line-argument-list*)
              nil)
          (error "error: position ~A is out of bounds: list has ~A ~A."
                 (+ .nth. 1)
                 (argc*)
                 (if (> (argc*) 1) ; use position, if there is only 1, or positions.
                     "indices"
                     (if (< (argc*) 1)
                         "indices"
                         "index"))))))

;; cease treating argc* like an inline function, so that other functions will call it normally
(declaim (notinline argc*))
