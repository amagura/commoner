;(defun odd (list)
  ;"returns the items appearing at odd indices within a list"
  ;(do ((l list (cddr l))
      ;(x '() (cons (car l) x)))
  ;((null l)
   ;(nreverse x))))

;; Die
;; (die (exit format &rest args))
;(defun die (exit format &rest args)
  ;"Die in error with custom error message"
  ;(with-safe-io-syntax )

(defun getenv* (name &optional default)
  "get enviroment variables"
  #+cmu
  (let ((x (assoc name ext:*environment-list*
                  :test #'string=)))
    (if x (cdr x) default))
  #-cmu
  (or
    #+allegro   (sys:getenv name)
    #+clisp     (ext:getenv name)
    #+ecl       (si:getenv name)
    #+sbcl      (sb-unix::posix-getenv name)
    #+lispworks (lispworks:environment-variable name)
    default))

(defun exit* (&optional code)
  (or
    ;; This group from "clocc-port/ext.lisp"
    #+clisp             (#+lisp=cl ext:quit #-lisp=cl lisp:quit code)
    #+sbcl              (sb-ext:exit :code code)
    #+allegro           (excl:exit code)
    #+cormanlisp        (win32:exitprocess code)
    #+gcl               (lisp:bye code)           ; XXX or is it LISP::QUIT?
    #+lispworks         (lw:quit :status code)
    #+lucid             (lcl:quit code)
    ;; This group from Maxima
    #+kcl               (lisp::bye)               ; XXX Does this take an arg?
    #+scl               (ext:quit code)           ; XXX Pretty sure this *does* take an arg.
    #+(or openmcl mcl)  (ccl::quit)
    #+abcl              (cl-user::quit)
    #+ecl               (si:quit)
    ;; This group from <hebi...@math.uni.wroc.pl>
    #+poplog            (poplog::bye)             ; XXX does this take an arg?
    #-(or allegro clisp
          cmu cormalisp
          gcl lispworks
          lucid sbcl
          kcl scl
          openmcl mcl
          abcl ecl)
    (not-implemented-error 'exit*)))

(defun unquote (quoted-sexp)
  ;; this takes advantage of the fact that
  ;; function arguments are evaluated before
  ;; being processed
  ;; XXX this is basically just a trick to evaluate
  ;; some code once (in case it is quoted, but we want it to act like it isn't)
  quoted-sexp)

#|/////////////////////////////////|#
;;;; Additional Flow Control
#|/////////////////////////////////|#
(defmacro nest (&rest .rest.) ;; taken from uiop/utility.lisp
  "macro that keeps indentation under control"
  (reduce #'(lambda (outer inner) `(,@outer ,inner))
          .rest. :from-end t))

(defmacro if-let (bindings &body (then-form &optional else-form)) ;; from uiop/utility.lisp
  "bindings can be (var form) or ((var1 form1) ...)"
  (let* ((binding-list (if (and (consp bindings) (symbolp (car bindings)))
                           (list bindings)
                           bindings))
         (variables (mapcar #'car binding-list)))
    `(let ,binding-list
       (if (and ,@variables)
           ,then-form
           ,else-form))))

(defun length= (text expected-length)
  ; test if (= (length text) expected-length) is true
  (= (length text) expected-length))

(defun if-length (cond then-form &optional else-form)
  (if (length= (car cond) (cadr cond))
      then-form
      (if (not (null else-form))
          else-form)))

(defun not-nullp (sexp)
  ;; A very basic NOT NULL
  (not (null sexp)))

(defmacro undefinedp (symbol)
  ;; returns T if the symbol is not defined
  ;; and nil if it is defined
  (let ((%z% (gensym "masked-symbol")))
    `(handler-case (and (let ((,%z% ,symbol)) ,%z%) nil) ((or undefined-function unbound-variable) () t))))

(defmacro definedp (symbol)
  ;; trivial macro that returns nil if a variable is not defined
  ;; and t if it is defined
  (let ((%z% (gensym "masked-symbol")))
    `(handler-case (and (let ((,%z% ,symbol)) ,%z%) t) ((or undefined-function unbound-variable) () nil))))
