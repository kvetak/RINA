//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

package rina.src.DIF.Enrollment;

 simple Enrollment
{
    parameters:
    	@display("i=block/arrival");
    	xml enrolConfigData = default(xml("<Enrollment></Enrollment>"));
    	xml configData = default(enrolConfigData);
    	
    	bool isSelfEnrolled = default(false);
	    
	    //Authentication
        int authType							= default(1);
        string authName							= default("0");
        string authPassword						= default("0");
        string authOther						= default("0");
        
        int maxConRetries						= default(5);
        
        //signals
        @signal[Enrollment-CACEDataSend](type=CDAPMessage?);
        @signal[Enrollment-StartEnrollmentRequest];
        @signal[Enrollment-StartEnrollmentResponse];
        @signal[Enrollment-StopEnrollmentRequest];
        @signal[Enrollment-StopEnrollmentResponse];
        @signal[Enrollment-StartOperationRequest];
        @signal[Enrollment-StartOperationResponse];
        @signal[Enrollment-Finished];
        
        
}
